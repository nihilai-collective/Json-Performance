
----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1020.61 | 0.165964 | 96.2417ms | 905 | 1280 | 2521.23 | 845.645 | 1.00178 | 1(Win) | true |
| Glaze | 123.47 | 0.133469 | 709.165ms | 905 | 30 | 2611.32 | 6990.17 | 0.0424226 | 2(Loss) | true |
