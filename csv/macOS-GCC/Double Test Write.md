
----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 276.494 | 1.28806 | 687.724ms | 1997 | 160 | 1.25944e+06 | 6888 | 2.99043 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 255.791 | 1.89907 | 696.136ms | 1811 | 40 | 657671 | 6752 | 0.094697 | 1(Tie) | true |
| Glaze | 196.903 | 0.203481 | 888.117ms | 1798 | 2560 | 803827 | 8708.4 | 0.214044 | 3(Loss) | true |
