
----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 819.43 | 0.0703174 | 2145.78ms | 11812 | 640 | 59803.9 | 13747.1 | 0.14124 | 6.23547 | 28.9379 | 5.78945 | 0.0153917 | 2.05035e-05 | 6.61404e-06 | 1(Win) | true |
| simdjson (ondemand) | 718.685 | 0.0857545 | 2342.43ms | 11812 | 4890 | 883471 | 15674.2 | 0.164553 | 7.16257 | 32.488 | 5.95234 | 0.0122578 | 0.000101592 | 5.92445e-05 | 2(Loss) | true |
