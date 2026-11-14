
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3615 | 0.0360057 | 1466.46ms | 25388 | 2560 | 14887.5 | 6697.61 | 0.0973455 | 1.40646 | 6.77734 | 0.960533 | 0.00270617 | 1.03395e-05 | 2.43102e-06 | 1(Win) | true |
| Jsonifier | 3532.35 | 0.0398332 | 1476.57ms | 25388 | 4890 | 36452.6 | 6854.33 | 0.132457 | 1.43847 | 6.807 | 1.29301 | 0.00403223 | 1.81317e-05 | 8.90072e-06 | 2(Loss) | true |
| simdjson (reflection) | 3167.62 | 0.0271807 | 1555.93ms | 25388 | 4890 | 21106.7 | 7643.55 | 0.0327646 | 1.60389 | 6.74823 | 0.977824 | 0.00141667 | 1.50305e-05 | 5.03434e-06 | 3(Loss) | true |
| Glaze | 2424.13 | 0.0349662 | 1792.69ms | 25388 | 1280 | 15611.8 | 9987.86 | 0.0693039 | 2.09357 | 8.93158 | 1.6984 | 0.00532797 | 1.10473e-05 | 2.83106e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2372.7 | 0.0323903 | 1819.88ms | 25388 | 2560 | 27966.8 | 10204.4 | 0.158073 | 2.14024 | 8.61978 | 1.43887 | 0.0035352 | 1.72326e-05 | 6.75454e-06 | 5(Loss) | true |
