
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2771.92 | 0.098277 | 8528.11ms | 7351818 | 80 | 4.94335e+08 | 2.52938e+06 | 0.241614 | 1.82098 | 7.5997 | 1.43562 | 0.0120632 | 0.0547921 | 0.00070051 | 1(Win) | true |
| Jsonifier | 2752.24 | 0.0484108 | 8614.92ms | 7351818 | 160 | 2.43344e+08 | 2.54746e+06 | 0.151861 | 1.82908 | 7.64215 | 1.7349 | 0.00873832 | 0.0276732 | 8.62593e-05 | 2(Loss) | true |
| simdjson (reflection) | 2662.38 | 0.0390797 | 8828.18ms | 7351818 | 80 | 8.47312e+07 | 2.63345e+06 | 0.127854 | 1.89465 | 8.30605 | 1.34339 | 0.00653632 | 0.0519289 | 0.000215011 | 3(Loss) | true |
| Glaze | 2193.16 | 0.12415 | 5147.68ms | 7351818 | 30 | 4.72562e+08 | 3.19686e+06 | 0.0969191 | 2.30393 | 10.4908 | 2.06525 | 0.00859066 | 0.0273758 | 0.000170103 | 4(Loss) | true |
| simdjson (ondemand) | 2166.36 | 0.0910252 | 5217.17ms | 7351818 | 80 | 6.94289e+08 | 3.23641e+06 | 0.0612736 | 2.33082 | 9.63014 | 1.64996 | 0.00781907 | 0.053603 | 0.000820557 | 5(Loss) | true |
