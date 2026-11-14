
----
### Github Events Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1255.86 | 0.0737712 | 6239.29ms | 65103 | 320 | 425640 | 49437.8 | 0.0172848 | 4.1013 | 15.0459 | 2.96008 | 0.0119704 | 1.86723e-05 | 1.10402e-05 | 1(Win) | true |
| simdjson (ondemand) | 619.29 | 0.088312 | 5824.58ms | 65103 | 640 | 5.01688e+06 | 100255 | 0.164895 | 8.31355 | 31.4199 | 5.54554 | 0.042053 | 2.81765e-05 | 8.92816e-06 | 2(Loss) | true |
