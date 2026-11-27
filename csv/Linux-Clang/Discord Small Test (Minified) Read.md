
----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2215.25 | 0.100798 | 942.779ms | 4857 | 4890 | 21722 | 2090.96 | 0.0710675 | 2.32612 | 8.75448 | 1.73708 | 0.00119293 | 4.88827e-05 | 1.49048e-05 | 1(Win) | true |
| Glaze | 1702.71 | 0.0758213 | 1008.61ms | 4857 | 4890 | 20804 | 2720.36 | 0.0930927 | 3.0255 | 11.8964 | 2.27363 | 0.000326643 | 9.19551e-05 | 3.84409e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1678.25 | 0.120713 | 1012.6ms | 4857 | 2560 | 28416.5 | 2760.01 | 0.14133 | 3.05847 | 12.5976 | 2.15627 | 0.00153274 | 5.93538e-05 | 2.21973e-05 | 3(Loss) | true |
| simdjson (ondemand) | 767.079 | 0.171431 | 1346.25ms | 4857 | 640 | 68583 | 6038.48 | 0.278654 | 6.63492 | 23.4638 | 3.91692 | 0.00362814 | 3.73173e-05 | 6.75571e-06 | 4(Loss) | true |
