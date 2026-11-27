
----
### Random Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1394.15 | 0.0381456 | 1096.92ms | 4926 | 4890 | 8079.19 | 3369.65 | 0.0262293 | 3.735 | 14.4872 | 2.64779 | 0.00901543 | 5.92823e-05 | 2.28328e-05 | 1(Win) | true |
| simdjson (ondemand) | 1149.49 | 0.0629636 | 1170.34ms | 4926 | 1280 | 8475.55 | 4086.85 | 0.197746 | 4.49663 | 16.8886 | 2.81628 | 0.0107887 | 6.20115e-05 | 2.82303e-05 | 2(Loss) | true |
