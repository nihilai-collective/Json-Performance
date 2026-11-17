
----
### Github Events Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1136.86 | 0.0213504 | 5769.04ms | 53331 | 4890 | 446137 | 44737.7 | 0.0914339 | 4.49288 | 17.2077 | 3.39326 | 0.0137668 | 1.52882e-05 | 6.94049e-06 | 1(Win) | true |
| simdjson (ondemand) | 481.651 | 0.073828 | 6138.3ms | 53331 | 1280 | 7.77941e+06 | 105596 | 0.207927 | 10.6336 | 38.5623 | 6.85593 | 0.0625555 | 2.22373e-05 | 8.51111e-06 | 2(Loss) | true |
