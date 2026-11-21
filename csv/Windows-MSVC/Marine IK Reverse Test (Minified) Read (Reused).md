
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 780.575 | 0.422906 | 8519.08ms | 1834197 | 40 | 3.5926e+09 | 2.24094e+06 | 1.07673 | 3.17168 | 1(Win) | true |
| Jsonifier (two-stage) | 657.011 | 0.422727 | 9781.02ms | 1834197 | 80 | 1.01334e+10 | 2.6624e+06 | 0.243087 | 3.76803 | 2(Loss) | true |
| Glaze | 208.938 | 0.410933 | 6346.77ms | 1834197 | 40 | 4.73432e+10 | 8.37198e+06 | 1.06563 | 11.8493 | 3(Loss) | true |
| simdjson (ondemand) | 127.306 | 1.82091 | 10193.2ms | 1834197 | 30 | 1.87799e+12 | 1.37403e+07 | 0.448719 | 19.4472 | 4(Loss) | true |
