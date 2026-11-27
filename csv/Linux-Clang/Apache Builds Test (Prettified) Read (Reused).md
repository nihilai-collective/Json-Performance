
----
### Apache Builds Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2617.7 | 0.0361561 | 6521.32ms | 124597 | 640 | 172393 | 45392.9 | 0.0612709 | 1.93338 | 8.90903 | 1.56781 | 0.00462433 | 6.05703e-06 | 3.86245e-06 | 1(Win) | true |
| simdjson (ondemand) | 2169.41 | 0.0339585 | 7464.05ms | 124597 | 1280 | 442833 | 54773 | 0.0629927 | 2.345 | 9.9824 | 1.70916 | 0.00632444 | 1.94502e-05 | 1.52241e-05 | 2(Loss) | true |
