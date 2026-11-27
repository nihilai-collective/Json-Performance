
----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2172.85 | 0.0730021 | 845.94ms | 2821 | 4890 | 3995.07 | 1238.15 | 0.0715093 | 2.44574 | 9.0833 | 1.59624 | 0.000360066 | 0.000141141 | 8.48877e-05 | 1(Win) | true |
| simdjson (ondemand) | 2019.9 | 0.0379587 | 851.604ms | 2821 | 4890 | 1249.91 | 1331.9 | 0.0556036 | 2.62438 | 9.93584 | 1.52818 | 0.000365793 | 5.16141e-05 | 1.60931e-05 | 2(Loss) | true |
