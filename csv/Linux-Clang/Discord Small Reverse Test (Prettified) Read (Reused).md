
----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1027.83 | 0.0415425 | 1369.91ms | 6701 | 1280 | 8539.42 | 6217.51 | 0.0296579 | 5.04158 | 21.4205 | 4.25444 | 0.00507002 | 2.59989e-05 | 6.06253e-06 | 1(Win) | true |
| simdjson (ondemand) | 326.925 | 0.0451011 | 2708.82ms | 6701 | 160 | 12435.9 | 19547.5 | 0.00671395 | 15.7924 | 82.2855 | 15.7747 | 0.0320325 | 3.54425e-05 | 3.73079e-06 | 2(Loss) | true |
