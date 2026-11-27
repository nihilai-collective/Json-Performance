
----
### Twitter Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12106.6 | 0.257845 | 752.267ms | 4300 | 40 | 30.5122 | 338.725 | 0.125628 | 0.475174 | 1.13442 | 0.159302 | 0.000232558 | 2.32558e-05 | 0 | 1(Win) | true |
| Glaze | 3567.32 | 0.227259 | 839.242ms | 4300 | 4890 | 33373.7 | 1149.55 | 0.0550931 | 1.50157 | 3.5886 | 0.603954 | 0.00062453 | 6.43458e-05 | 1.73111e-05 | 2(Loss) | true |
| simdjson (reflection) | 556.547 | 0.0749777 | 1469.88ms | 4300 | 4890 | 149248 | 7368.3 | 0.108556 | 9.29244 | 33.594 | 7.42861 | 0.00898954 | 0.000141057 | 5.0887e-05 | 3(Loss) | true |
