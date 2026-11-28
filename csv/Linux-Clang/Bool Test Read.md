
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1794.09 | 0.161919 | 48.1883ms | 905 | 30 | 18.2023 | 481.067 | 0 | 1.30033 | 1(Win) | true |
| Glaze | 1415.2 | 0.0835591 | 67.4987ms | 905 | 320 | 83.0993 | 609.859 | 0.0281748 | 1.67166 | 2(Loss) | true |
| simdjson (ondemand) | 413.456 | 0.0600152 | 200.939ms | 905 | 30 | 47.0851 | 2087.47 | 0.0127763 | 5.90947 | 3(Loss) | true |
