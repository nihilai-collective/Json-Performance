
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2777.31 | 0.0779692 | 8594.51ms | 7351818 | 160 | 6.1988e+08 | 2.52447e+06 | 0.05195 | 1.80223 | 7.6058 | 1.41341 | 0.0115845 | 0.0546758 | 0.0010712 | 1(Win) | true |
| Jsonifier | 2638.1 | 0.0649647 | 8972.59ms | 7351818 | 160 | 4.7696e+08 | 2.65768e+06 | 0.256501 | 1.89834 | 8.03736 | 1.90278 | 0.00870516 | 0.0274322 | 0.000449578 | 2(Loss) | true |
| simdjson (reflection) | 2430.8 | 0.13087 | 9529.09ms | 7351818 | 160 | 2.27979e+09 | 2.88434e+06 | 0.105024 | 2.0645 | 8.95056 | 1.47816 | 0.00790538 | 0.0521445 | 0.0041338 | 3(Loss) | true |
| Glaze | 2220.28 | 0.126431 | 5102.93ms | 7351818 | 30 | 4.78191e+08 | 3.15781e+06 | 0.195096 | 2.26426 | 10.49 | 2.06508 | 0.00855446 | 0.0275965 | 0.000573513 | 4(Loss) | true |
| simdjson (ondemand) | 2079.99 | 0.257811 | 5343.92ms | 7351818 | 40 | 3.02084e+09 | 3.3708e+06 | 0.376768 | 2.41266 | 9.75062 | 1.69725 | 0.00909191 | 0.0536395 | 0.010965 | 5(Loss) | true |
