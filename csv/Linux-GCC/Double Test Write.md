
----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 344.959 | 0.0233628 | 503.07ms | 1811 | 40 | 54.7282 | 5006.7 | 0.0253058 | 7.13704 | 1(Win) | true |
| simdjson (reflection) | 314.92 | 0.0372441 | 611.819ms | 1997 | 40 | 202.922 | 6047.52 | 0.332498 | 7.82695 | 2(Loss) | true |
| Glaze | 266.11 | 0.0306941 | 656.054ms | 1798 | 30 | 117.352 | 6443.6 | 0.016034 | 9.2672 | 3(Loss) | true |
