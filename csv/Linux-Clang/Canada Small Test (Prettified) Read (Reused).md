
----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2148.51 | 0.064062 | 1342.21ms | 11579 | 2560 | 27753 | 5139.65 | 0.254081 | 2.36792 | 11.7488 | 1.87944 | 0.000746232 | 5.72494e-05 | 2.97886e-05 | 1(Win) | true |
| Jsonifier (generic) | 1995.64 | 0.116459 | 1376.84ms | 11579 | 40 | 1661.05 | 5533.35 | 0.154757 | 2.55383 | 12.1181 | 2.16487 | 0.000995336 | 1.51136e-05 | 0 | 2(Loss) | true |
