import sqlite3 

"""
Exemplo de entrada:
['Sim', 'Esperando o carrinho.', 'START', '', 
'Check 1->321116', '', 'Check 2->187724', 'Final->1176', 
'Final de percurso!', 'Tempo final:  510016', 
'Iniciar corrida?\n\r', '']
"""

def extrairTempo(data: [str]) -> int:
        temposExtraidosString = [data[4][9:], data[6][9:], data[7][7:]]
        temposExtraidos = [int(numero) for numero in temposExtraidosString]

        return temposExtraidos



data = ['Sim', 'Esperando o carrinho.', 'START', '', 
        'Check 1->321116', '', 'Check 2->187724', 'Final->1176', 
        'Final de percurso!', 'Tempo final:  510016', 
        'Iniciar corrida?\n\r', '']

print(extrairTempo(data))