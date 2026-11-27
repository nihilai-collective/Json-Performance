
----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 212.954 | 1.23039 | 6607.26ms | 1834197 | 30 | 3.06425e+11 | 8.2141e+06 | 0.0494433 | 11.6257 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 204.539 | 1.51723 | 6727.83ms | 1834197 | 40 | 6.73443e+11 | 8.55203e+06 | 2.55615 | 12.104 | -(Loss) | false |
