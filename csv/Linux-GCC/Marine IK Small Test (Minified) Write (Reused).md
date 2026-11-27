
----
### Marine IK Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1951.41 | 0.402792 | 960.616ms | 4918 | 40 | 3748.87 | 2403.47 | 0.0364189 | 2.68358 | 9.57361 | 0.795039 | 0.000640504 | 4.57503e-05 | 2.54168e-05 | 1(Win) | true |
| Jsonifier | 1456.03 | 0.170993 | 1043.02ms | 4918 | 2560 | 77667 | 3221.21 | 0.383527 | 3.59921 | 9.00427 | 0.467874 | 0.000493722 | 4.71006e-05 | 1.52501e-05 | 2(Loss) | true |
| Glaze | 1313.04 | 0.0499796 | 1056.04ms | 4604 | 4890 | 13658.6 | 3343.92 | 0.260921 | 3.97139 | 12.2024 | 0.96829 | 0.000870364 | 0.000120727 | 7.1246e-05 | 3(Loss) | true |
