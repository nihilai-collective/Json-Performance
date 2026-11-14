
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1793.47 | 0.120347 | 155.836ms | 2889 | 4890 | 16714.3 | 1536.22 | 0.104743 | 1.67463 | 1(Win) | true |
| Glaze | 1690.29 | 0.316307 | 168.844ms | 2889 | 80 | 2126.58 | 1630 | 0 | 1.78242 | 2(Loss) | true |
| Jsonifier (two-stage) | 1431.49 | 0.202364 | 197.126ms | 2889 | 2560 | 38835.4 | 1924.69 | 0.13413 | 2.10288 | 3(Loss) | true |
| simdjson (ondemand) | 1363.39 | 0.226888 | 204.062ms | 2889 | 4890 | 102798 | 2020.82 | 0.168003 | 2.20795 | 4(Loss) | true |
