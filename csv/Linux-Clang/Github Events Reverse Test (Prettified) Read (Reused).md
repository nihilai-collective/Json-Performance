
----
### Github Events Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1281.8 | 0.0281669 | 6190.18ms | 65103 | 4890 | 910230 | 48437.6 | 0.0764608 | 4.00573 | 14.6108 | 2.89656 | 0.0116007 | 0.000100106 | 8.042e-05 | 1(Win) | true |
| simdjson (ondemand) | 610.805 | 0.074194 | 5904.23ms | 65103 | 1280 | 7.28021e+06 | 101648 | 0.171313 | 8.37291 | 31.3805 | 5.53887 | 0.0438183 | 5.94011e-05 | 4.48568e-05 | 2(Loss) | true |
