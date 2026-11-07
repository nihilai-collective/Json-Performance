
----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14551.2 | 0.117701 | 3146.83ms | 475954 | 4890 | 6.59179e+06 | 31193.6 | 0.283016 | 0.169945 | 1(Win) | true |
| Glaze | 5713.07 | 0.0847683 | 8031.52ms | 475954 | 2560 | 1.16118e+07 | 79450.3 | 0.000442492 | 0.43315 | 2(Loss) | true |
