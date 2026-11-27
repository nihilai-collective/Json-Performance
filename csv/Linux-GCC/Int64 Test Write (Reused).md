
----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2433.3 | 0.0772514 | 65.1067ms | 1313 | 160 | 25.2855 | 514.6 | 0.0922196 | 0.963647 | 1(Win) | true |
| Jsonifier | 2175.8 | 0.0979928 | 66.4009ms | 1313 | 80 | 25.443 | 575.5 | 0.117152 | 1.08211 | 2(Loss) | true |
| Glaze | 1299.37 | 0.0700444 | 103.674ms | 1313 | 40 | 18.225 | 963.675 | 0.116604 | 1.84798 | 3(Loss) | true |
