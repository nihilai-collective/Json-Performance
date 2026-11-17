
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5524.14 | 0.307275 | 54.8285ms | 2889 | 160 | 375.786 | 498.75 | 0.25 | 0.423133 | 1(Win) | true |
| Jsonifier (two-stage) | 5474.4 | 0.159374 | 55.5005ms | 2889 | 640 | 411.752 | 503.281 | 0.154991 | 0.426752 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 2946.7 | 0.816858 | 127.857ms | 2889 | 40 | 2333.33 | 935 | 0.531915 | 0.812894 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2935.66 | 0.144985 | 104.074ms | 2889 | 1280 | 2369.96 | 938.516 | 0.406234 | 0.818825 | 3(Tie) | true |
