
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2447.54 | 0.33433 | 9966.04ms | 7351818 | 80 | 7.33787e+09 | 2.86461e+06 | 0.761354 | 1.01153 | 1(Win) | true |
| Jsonifier DID NOT CONVERGE | 2347.98 | 0.181787 | 10127.6ms | 7351818 | 160 | 4.71463e+09 | 2.98608e+06 | 10.1532 | 1.05443 | -(Loss) | false |
| Glaze DID NOT CONVERGE | 732.054 | 0.359044 | 7025.5ms | 7351818 | 40 | 4.72997e+10 | 9.57749e+06 | 2.77867 | 3.38202 | -(Loss) | false |
| simdjson (ondemand) DID NOT CONVERGE | 507.962 | 1.57963 | 10037.2ms | 7351818 | 40 | 1.9015e+12 | 1.38027e+07 | 5.19192 | 4.87397 | -(Loss) | false |
