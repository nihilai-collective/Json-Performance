
----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1742.53 | 2.0052 | 52.9009ms | 905 | 2560 | 252517 | 495.3 | 0.78125 | 1(Win) | true |
| simdjson (reflection) | 207.191 | 0.791526 | 422.582ms | 905 | 320 | 347885 | 4165.6 | 0.401683 | 2(Loss) | true |
| Glaze | 117.534 | 0.641381 | 760.499ms | 905 | 320 | 709827 | 7343.2 | 1.20176 | 3(Loss) | true |
