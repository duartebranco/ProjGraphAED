import matplotlib.pyplot as plt

vertices = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50]
vProcessados = [585, 9595, 49155, 156390, 383425, 797385, 1480395, 2529580, 4057065, 6189975]
aAdicionadas = [20, 90, 210, 380, 600, 870, 1190, 1560, 1980, 2450]

plt.figure()
plt.plot(vertices, vProcessados, label='Vertices Processados')
plt.xlabel('Número de Vértices', fontsize = 15)
plt.ylabel('Vértices Processados', fontsize = 15)
plt.title("Vértices processados em função do num de vértices", fontsize = 15)
plt.show()


plt.figure()
plt.plot(vertices, aAdicionadas, label='Arestas Adicionadas')
plt.xlabel('Número de Vértices', fontsize = 15)
plt.ylabel('Arestas Adicionadas', fontsize = 15)
plt.title("Arestas adicionadas em função do num de vértices", fontsize = 15)
plt.show()