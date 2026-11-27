
----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 939.417 | 0.0614411 | 6475.4ms | 1834197 | 160 | 2.09418e+08 | 1.86204e+06 | 0.596058 | 5.3646 | 22.3226 | 4.95189 | 0.0366781 | 0.0575837 | 7.11858e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 797.202 | 0.0673691 | 7587.47ms | 1834197 | 80 | 1.7481e+08 | 2.19421e+06 | 0.119653 | 6.32897 | 26.5892 | 5.46282 | 0.0457477 | 0.121513 | 9.62819e-05 | 2(Loss) | true |
| simdjson (reflection) | 750.788 | 0.0770302 | 7973.94ms | 1834197 | 30 | 9.66275e+07 | 2.32985e+06 | 0.0617497 | 6.73047 | 29.2821 | 5.2941 | 0.0266098 | 0.112196 | 7.28929e-05 | 3(Loss) | true |
| Glaze | 709.454 | 0.0837918 | 8413.44ms | 1834197 | 160 | 6.82915e+08 | 2.46559e+06 | 0.0236396 | 7.1758 | 29.3585 | 5.6248 | 0.0333574 | 0.0588438 | 0.000661928 | 4(Loss) | true |
| simdjson (ondemand) | 624.285 | 0.122359 | 9439.84ms | 1834197 | 80 | 9.40347e+08 | 2.80197e+06 | 0.0258948 | 8.15973 | 33.9708 | 6.4563 | 0.0318814 | 0.118999 | 0.000319915 | 5(Loss) | true |
