
----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8161.83 | 0.298307 | 5656.22ms | 466906 | 320 | 8.47539e+06 | 54555.9 | 0.444234 | 0.303145 | 1(Win) | true |
| Jsonifier | 7994.26 | 0.113076 | 5631.29ms | 466906 | 2560 | 1.01551e+07 | 55699.5 | 0.171386 | 0.309515 | 2(Loss) | true |
| simdjson (ondemand) | 3981.89 | 0.114282 | 5809.48ms | 466906 | 2560 | 4.18095e+07 | 111825 | 0.125039 | 0.621574 | 3(Loss) | true |
| Glaze | 2880.76 | 0.195229 | 8075.86ms | 466906 | 320 | 2.91395e+07 | 154569 | 0.612887 | 0.859233 | 4(Loss) | true |
