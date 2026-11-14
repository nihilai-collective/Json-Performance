
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 2042.11 | 1.02752 | 5823.33ms | 7351818 | 30 | 3.73368e+10 | 3.43333e+06 | 1.87719 | 1.48821 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2020.37 | 1.42382 | 5755.06ms | 7351818 | 40 | 9.76553e+10 | 3.47028e+06 | 1.1577 | 1.5041 | 1(Tie) | true |
| Glaze | 1112.84 | 0.643217 | 10283.2ms | 7351818 | 80 | 1.31381e+11 | 6.30034e+06 | 1.57551 | 2.73102 | 3(Loss) | true |
| simdjson (ondemand) | 649.756 | 0.615117 | 7858.07ms | 7351818 | 30 | 1.32168e+11 | 1.07906e+07 | 0.523538 | 4.6776 | 4(Loss) | true |
