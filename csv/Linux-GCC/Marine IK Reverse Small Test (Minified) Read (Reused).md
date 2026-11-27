
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1050.38 | 0.0476083 | 1226.91ms | 4604 | 4890 | 19366.4 | 4180.11 | 0.022904 | 4.94778 | 20.2954 | 4.44375 | 0.00267763 | 9.70082e-05 | 3.29579e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 887.578 | 0.0612225 | 1303.45ms | 4604 | 2560 | 23481.1 | 4946.85 | 0.0554733 | 5.85082 | 24.9628 | 4.93039 | 0.00246974 | 7.61905e-05 | 2.36717e-05 | 2(Loss) | true |
| simdjson (reflection) | 746.91 | 0.0472653 | 1400.78ms | 4604 | 4890 | 37750.9 | 5878.5 | 0.0703501 | 6.94144 | 26.0028 | 4.88986 | 0.00278055 | 0.000176427 | 0.000104559 | 3(Loss) | true |
| Glaze | 732.54 | 0.0320385 | 1410.85ms | 4604 | 4890 | 18032.8 | 5993.83 | 0.0996004 | 7.0528 | 29.3934 | 5.91073 | 0.00673288 | 8.42159e-05 | 3.58006e-05 | 4(Loss) | true |
| simdjson (ondemand) | 544.52 | 0.0501121 | 1626.9ms | 4604 | 2560 | 41799.1 | 8063.46 | 0.275278 | 9.45162 | 33.0647 | 6.59489 | 0.0103292 | 0.000143388 | 6.99969e-05 | 5(Loss) | true |
