
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1612.62 | 3.70433 | 53.7638ms | 905 | 640 | 251554 | 535.2 | 0.904977 | 1(Win) | true |
| Glaze | 1387.02 | 1.4765 | 62.924ms | 905 | 4890 | 412774 | 622.253 | 0.772961 | 2(Loss) | true |
| simdjson (reflection) | 823.231 | 1.46953 | 112.108ms | 905 | 640 | 151911 | 1048.4 | 3.59684 | 3(Loss) | true |
| simdjson (ondemand) | 345.341 | 1.60036 | 231ms | 905 | 160 | 255951 | 2499.2 | 1.56047 | 4(Loss) | true |
