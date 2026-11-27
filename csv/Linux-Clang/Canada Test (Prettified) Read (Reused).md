
----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2122.47 | 0.234447 | 8718.78ms | 5212421 | 30 | 9.0449e+08 | 2.34206e+06 | 0.637813 | 1.16645 | 1(Win) | true |
| simdjson (ondemand) | 1973.22 | 0.0588443 | 9331.36ms | 5212421 | 80 | 1.75803e+08 | 2.5192e+06 | 0.0219619 | 1.25468 | 2(Loss) | true |
