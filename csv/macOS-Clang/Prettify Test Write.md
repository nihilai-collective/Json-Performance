
----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3267.36 | 0.296832 | 5312.09ms | 699405 | 40 | 1.46874e+07 | 204142 | 0.222641 | 1(Win) | true |
| Glaze | 2514.55 | 0.124665 | 6903.29ms | 699405 | 640 | 6.9985e+07 | 265258 | 0.104103 | 2(Loss) | true |
| simdjson (ondemand) | 1629.64 | 0.101101 | 5722.44ms | 767297 | 640 | 1.31897e+08 | 449025 | 0.703207 | 3(Loss) | true |
