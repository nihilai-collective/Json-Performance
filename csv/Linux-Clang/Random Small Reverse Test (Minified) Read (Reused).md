
----
### Random Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 945.841 | 0.0314117 | 1254.11ms | 4926 | 4890 | 11902.7 | 4966.8 | 0.0409655 | 5.49252 | 24.701 | 4.90723 | 0.00832468 | 3.15093e-05 | 3.69476e-06 | 1(Win) | true |
| simdjson (ondemand) | 497.398 | 0.0241287 | 1707.24ms | 4926 | 4890 | 25395.5 | 9444.74 | 0.0425097 | 10.4011 | 46.6251 | 8.39505 | 0.0227436 | 3.66155e-05 | 5.60442e-06 | 2(Loss) | true |
