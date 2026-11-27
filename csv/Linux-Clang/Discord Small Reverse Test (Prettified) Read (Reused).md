
----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1057.38 | 0.032349 | 1361.51ms | 6701 | 320 | 1223.17 | 6043.77 | 0.0293605 | 4.90691 | 21.3138 | 4.11909 | 0.00573422 | 1.53895e-05 | 1.86539e-06 | 1(Win) | true |
| simdjson (ondemand) | 313.837 | 0.0269686 | 2790.98ms | 6701 | 4890 | 147468 | 20362.7 | 0.0593821 | 16.3763 | 82.2553 | 15.7562 | 0.0318694 | 0.000129395 | 7.92544e-05 | 2(Loss) | true |
