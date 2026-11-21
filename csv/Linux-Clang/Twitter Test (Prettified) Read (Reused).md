
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3030.54 | 0.119701 | 5785.25ms | 631514 | 320 | 1.8108e+07 | 198730 | 0.0206447 | 0.816797 | 1(Win) | true |
| Glaze | 2262.92 | 0.253833 | 7606.38ms | 631514 | 40 | 1.8255e+07 | 266142 | 0.133697 | 1.09396 | 2(Loss) | true |
| Jsonifier | 1937.28 | 0.188816 | 8801.67ms | 631514 | 30 | 1.03367e+07 | 310879 | 0.185227 | 1.27784 | 3(Loss) | true |
| simdjson (ondemand) | 1370.09 | 0.139071 | 5969.45ms | 631514 | 80 | 2.98972e+07 | 439575 | 0.0565823 | 1.8069 | 4(Loss) | true |
