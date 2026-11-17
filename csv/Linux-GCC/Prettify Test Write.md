
----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5279.51 | 0.198494 | 6575.82ms | 699405 | 80 | 5.03103e+06 | 126338 | 0.337422 | 0.468844 | 1(Win) | true |
| Glaze | 3311.86 | 0.109368 | 5430.96ms | 699405 | 160 | 7.76273e+06 | 201399 | 0.702259 | 0.747467 | 2(Loss) | true |
| simdjson (ondemand) | 2652.7 | 0.11125 | 6987.34ms | 767297 | 320 | 3.01372e+07 | 275852 | 0.354678 | 0.933192 | 3(Loss) | true |
