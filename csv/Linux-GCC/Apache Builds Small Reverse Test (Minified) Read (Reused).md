
----
### Apache Builds Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1438.17 | 0.0429157 | 901.601ms | 2632 | 4890 | 2743.44 | 1745.33 | 0.0170064 | 3.66151 | 14.6155 | 2.80395 | 0.0046386 | 6.65865e-05 | 2.13667e-05 | 1(Win) | true |
| simdjson (ondemand) | 787.642 | 0.0515992 | 1044.85ms | 2632 | 1280 | 3461.07 | 3186.82 | 0.00877562 | 6.61804 | 27.6782 | 5.54597 | 0.0110078 | 3.91812e-05 | 7.71752e-06 | 2(Loss) | true |
