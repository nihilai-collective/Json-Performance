
----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2221.76 | 0.0228949 | 60.1233ms | 1213 | 640 | 9.09458 | 520.67 | 0.0590836 | 1.0562 | 1(Win) | true |
| Jsonifier | 2138.8 | 0.156515 | 64.4654ms | 1213 | 30 | 21.4989 | 540.867 | 0.0492793 | 1.09879 | 2(Loss) | true |
| Glaze | 1325.09 | 0.188261 | 97.8484ms | 1213 | 30 | 81.0345 | 873 | 0.0420184 | 1.8097 | 3(Loss) | true |
