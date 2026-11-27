
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2643.35 | 0.0954824 | 739.763ms | 905 | 640 | 62.2034 | 326.508 | 0.253465 | 2.18757 | 11.0365 | 1.73039 | 0.0011067 | 6.38812e-05 | 5.17956e-06 | 1(Win) | true |
| Glaze | 1890.15 | 0.0318559 | 756.234ms | 905 | 4890 | 103.465 | 456.617 | 0.171901 | 2.95959 | 13.6652 | 2.06519 | 0.00113729 | 6.55301e-05 | 1.44618e-05 | 2(Loss) | true |
| simdjson (reflection) | 1188.27 | 0.0488318 | 786.693ms | 905 | 2560 | 322.044 | 726.332 | 0.181839 | 4.56445 | 22.7326 | 5.37127 | 0.00430162 | 0.000106181 | 2.15815e-05 | 3(Loss) | true |
| simdjson (ondemand) | 489.994 | 0.143263 | 892.363ms | 905 | 160 | 1018.83 | 1761.4 | 0.0326338 | 10.7475 | 50.1293 | 9.45304 | 0.0649931 | 0.00019337 | 0 | 4(Loss) | true |
