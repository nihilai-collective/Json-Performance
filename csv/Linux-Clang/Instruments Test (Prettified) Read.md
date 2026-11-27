
----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3540.89 | 0.0714243 | 5687.85ms | 183677 | 2560 | 3.19607e+06 | 49470.1 | 0.0982563 | 1.43073 | 6.58341 | 1.31983 | 0.00163051 | 1.59204e-05 | 9.15968e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2974.9 | 0.0851214 | 6646.32ms | 183677 | 1280 | 3.21554e+06 | 58882.1 | 0.231951 | 1.70795 | 7.88234 | 1.33635 | 0.00185149 | 1.84299e-05 | 9.84235e-06 | 2(Loss) | true |
| Glaze | 2563.97 | 0.115927 | 7576.51ms | 183677 | 1280 | 8.02897e+06 | 68319 | 0.0816221 | 1.97022 | 9.22717 | 1.72705 | 0.0030796 | 2.38445e-05 | 1.34152e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1174.09 | 0.192318 | 7973.59ms | 183677 | 320 | 2.63447e+07 | 149194 | 0.125817 | 4.26561 | 18.772 | 2.62917 | 0.00237713 | 5.41201e-05 | 2.55884e-05 | 4(Loss) | true |
