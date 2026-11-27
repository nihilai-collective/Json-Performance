
----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 225.05 | 0.381803 | 2217.72ms | 4604 | 40 | 221949 | 19510 | 0.0854993 | 13.474 | 1(Win) | true |
| simdjson (ondemand) | 169.845 | 1.53775 | 2802.83ms | 4604 | 80 | 1.26423e+07 | 25851.2 | 0.409323 | 17.8796 | 2(Loss) | true |
