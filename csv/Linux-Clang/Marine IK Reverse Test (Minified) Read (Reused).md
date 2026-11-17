
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 937.613 | 0.0802131 | 6474.61ms | 1834197 | 160 | 3.58307e+08 | 1.86562e+06 | 0.0101437 | 5.3558 | 23.9289 | 5.22083 | 0.029942 | 0.055453 | 0.000525666 | 1(Win) | true |
| Jsonifier (two-stage) | 796.261 | 0.15896 | 7567.49ms | 1834197 | 30 | 3.65826e+08 | 2.1968e+06 | 0.00870433 | 6.32838 | 28.5836 | 5.90845 | 0.0326513 | 0.118954 | 0.000844257 | 2(Loss) | true |
| Glaze | 735.303 | 0.0637571 | 8145.44ms | 1834197 | 160 | 3.68075e+08 | 2.37892e+06 | 0.181983 | 6.85445 | 28.9905 | 5.79182 | 0.034832 | 0.0586832 | 0.000206276 | 3(Loss) | true |
| simdjson (ondemand) | 635.733 | 0.0985709 | 9286.78ms | 1834197 | 80 | 5.88478e+08 | 2.75151e+06 | 0.181647 | 7.92477 | 34.2442 | 5.59991 | 0.0410692 | 0.118457 | 0.00821519 | 4(Loss) | true |
