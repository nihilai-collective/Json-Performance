
----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1522.7 | 0.0231543 | 7934.29ms | 94653 | 4890 | 921326 | 59281.8 | 0.0510307 | 3.33441 | 16.5582 | 3.26323 | 0.00738866 | 1.27168e-05 | 7.93556e-06 | 1(Win) | true |
| simdjson (ondemand) | 809.529 | 0.113411 | 6722.93ms | 94653 | 40 | 639697 | 111507 | 0.413591 | 6.2436 | 30.4059 | 6.21247 | 0.0109571 | 1.0829e-05 | 3.16947e-06 | 2(Loss) | true |
