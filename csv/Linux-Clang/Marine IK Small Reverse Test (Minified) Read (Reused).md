
----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 363.115 | 0.109044 | 2032.63ms | 4604 | 320 | 55633.5 | 12091.8 | 0.0300139 | 14.2182 | 62.9796 | 13.8456 | 0.0159915 | 0.000204985 | 0.000131679 | 1(Win) | true |
| simdjson (ondemand) | 257.609 | 0.0925452 | 2533.93ms | 4604 | 160 | 39808.5 | 17044.1 | 0.117059 | 20.027 | 105.913 | 21.1219 | 0.0207265 | 9.09535e-05 | 2.85078e-05 | 2(Loss) | true |
