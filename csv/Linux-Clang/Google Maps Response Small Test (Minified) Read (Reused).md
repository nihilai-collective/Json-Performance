
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1442.72 | 0.0232355 | 1043.48ms | 4390 | 4890 | 2223.2 | 2901.9 | 0.0294609 | 3.61941 | 16.5267 | 3.17084 | 0.00215614 | 4.48593e-05 | 8.05884e-06 | 1(Win) | true |
| simdjson (ondemand) | 1146.24 | 0.0532558 | 1104ms | 4390 | 640 | 2421.53 | 3652.48 | 0.00149729 | 4.54317 | 19.1497 | 3.2385 | 0.00419704 | 2.88297e-05 | 2.13554e-06 | 2(Loss) | true |
