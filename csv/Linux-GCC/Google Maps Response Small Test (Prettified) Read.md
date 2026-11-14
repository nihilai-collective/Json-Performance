
----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3198.07 | 0.0831927 | 1009.17ms | 9378 | 160 | 866.035 | 2796.55 | 0.0782826 | 1.63417 | 7.43549 | 1.11175 | 0.00173611 | 1.73278e-05 | 6.66453e-07 | 1(Win) | true |
| Jsonifier | 3041.27 | 0.0994821 | 1025.88ms | 9378 | 640 | 5477.48 | 2940.73 | 0.00196596 | 1.71424 | 7.50299 | 1.4534 | 0.00272863 | 1.23294e-05 | 3.33227e-07 | 2(Loss) | true |
| simdjson (reflection) | 2882.9 | 0.0452929 | 1035.14ms | 9378 | 4890 | 9654.52 | 3102.28 | 0.0707841 | 1.80669 | 7.16272 | 1.07262 | 0.00110924 | 3.05942e-05 | 1.07941e-05 | 3(Loss) | true |
| Glaze | 2224.99 | 0.0334614 | 1126.79ms | 9378 | 320 | 578.895 | 4019.59 | 0.0569412 | 2.33886 | 9.4982 | 1.81542 | 0.00365017 | 3.33227e-05 | 1.49952e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2221.77 | 0.0582185 | 1135.61ms | 9378 | 160 | 878.748 | 4025.42 | 0.154249 | 2.34234 | 9.04905 | 1.51962 | 0.00127692 | 2.7991e-05 | 1.19962e-05 | 5(Loss) | true |
