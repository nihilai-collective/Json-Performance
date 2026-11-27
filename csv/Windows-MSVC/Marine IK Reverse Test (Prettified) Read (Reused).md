
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 964.989 | 0.623013 | 5432.47ms | 7351818 | 40 | 8.19595e+10 | 7.26562e+06 | 0.084024 | 3.14951 | 1(Win) | true |
| simdjson (ondemand) | 688.556 | 1.10653 | 7155.01ms | 7351818 | 30 | 3.80856e+11 | 1.01825e+07 | 0.529839 | 4.41404 | 2(Loss) | true |
