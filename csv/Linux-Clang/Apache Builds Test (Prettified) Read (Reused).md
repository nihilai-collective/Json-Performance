
----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2688.77 | 0.0438813 | 6392.29ms | 124597 | 640 | 240683 | 44193 | 0.0338262 | 1.9037 | 8.88611 | 1.5922 | 0.00459208 | 2.59587e-06 | 4.38915e-07 | 1(Win) | true |
| simdjson (ondemand) | 2185 | 0.0509283 | 7406.38ms | 124597 | 640 | 490921 | 54382.2 | 0.105338 | 2.33692 | 9.97882 | 1.70865 | 0.00645432 | 5.06633e-06 | 6.14481e-07 | 2(Loss) | true |
