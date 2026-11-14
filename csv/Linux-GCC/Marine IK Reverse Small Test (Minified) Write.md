
----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1522.15 | 0.0675108 | 1031.9ms | 4918 | 80 | 346.177 | 3081.28 | 0.022723 | 3.42895 | 11.3817 | 1.34994 | 0.00075488 | 4.06669e-05 | 0 | 1(Win) | true |
| Jsonifier | 1412.53 | 0.131624 | 1034.96ms | 4604 | 4890 | 81857.8 | 3108.42 | 0.0828801 | 3.68754 | 9.5745 | 0.570157 | 0.000622292 | 5.40563e-05 | 2.59843e-05 | 2(Loss) | true |
| Glaze | 1250.17 | 0.0842623 | 1073.21ms | 4604 | 2560 | 22420.1 | 3512.09 | 0.0320759 | 4.15584 | 12.8553 | 1.10686 | 0.000455192 | 7.20332e-05 | 3.41924e-05 | 3(Loss) | true |
