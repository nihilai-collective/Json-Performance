
----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1536.02 | 0.994396 | 5169.64ms | 631514 | 160 | 2.43225e+09 | 392089 | 0.233751 | 1.97826 | 1(Win) | true |
| Glaze | 1399.83 | 0.498086 | 5619.65ms | 631514 | 320 | 1.46951e+09 | 430236 | 0.0462896 | 2.17087 | 2(Loss) | true |
| Jsonifier (two-stage) | 1348.22 | 0.610908 | 5681.99ms | 631514 | 640 | 4.76622e+09 | 446705 | 0.82857 | 2.25368 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1138.73 | 0.617828 | 6731.68ms | 631514 | 640 | 6.83344e+09 | 528886 | 4.0114 | 2.66838 | -(Loss) | false |
