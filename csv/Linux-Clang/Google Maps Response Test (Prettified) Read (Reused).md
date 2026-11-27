
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3981.39 | 0.0854319 | 1395.35ms | 25388 | 2560 | 69098.4 | 6081.27 | 0.0282743 | 1.27902 | 6.03029 | 1.13022 | 0.00308376 | 1.03241e-05 | 2.35409e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 3175.82 | 0.0678776 | 1548.05ms | 25388 | 2560 | 68554.9 | 7623.82 | 0.00419617 | 1.61042 | 7.64093 | 1.20269 | 0.00401349 | 2.74644e-05 | 1.52939e-05 | 2(Loss) | true |
| Glaze | 2530.38 | 0.064759 | 1737.34ms | 25388 | 2560 | 98293.8 | 9568.49 | 0.0734925 | 2.03055 | 9.12904 | 1.78139 | 0.0051393 | 3.38804e-05 | 1.75403e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2317.79 | 0.0565931 | 1836.75ms | 25388 | 4890 | 170902 | 10446.1 | 0.108889 | 2.19905 | 9.69167 | 1.50634 | 0.00328086 | 2.41165e-05 | 9.80287e-06 | 4(Loss) | true |
