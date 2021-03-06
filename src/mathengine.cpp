/*
 * This file is part of Kalk
 *
 * Copyright (C) 2020 Han Young <hanyoung@protonmail.com>
 *               2021 Rui Wang  <wangrui@jingos.com>     
 *
 * $BEGIN_LICENSE:GPL3+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 */

#include "mathengine.h"
#include <QDebug>

bool MathEngine::parse(QString expr)
{
    if(expr.count() == 0)
        return false ;
    
    bool haveExpr = containExpression(expr);
    if(expr.count() > 25 && !haveExpr){
        return false;
    }

    int parseResult = mDriver.parse(expr.toStdString());
    result_ = QString::number(mDriver.result , 'g' , 15);

    if (expr[expr.size() - 1] == QChar('.')){  
        if (expr.size() == 1)
            return false;
        if (!(expr[expr.size() - 2] >= QChar('0') && expr[expr.size() - 2] <= QChar('9')))
            return false;
        for (int i = (expr.size() - 2);i >= 0; i--){
            if (expr[i] == QChar('.'))
                return false;
            else if (expr[i] >= QChar('0') && expr[i] <= QChar('9')) 
                continue;
            else 
                break;
        }
    }
    
    emit resultChanged();
    return true;
}


bool MathEngine::containExpression(QString content)
{
    if(content.contains("+") 
            || content.contains("-") 
            || content.contains("x")
            || content.contains("÷")
            || content.contains("/")
            || content.contains("^")
            || content.contains("%")){
        return true ;
    }
    return false;
}
