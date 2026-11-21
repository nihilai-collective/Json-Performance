
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1006.84 | 0.709947 | 6287.98ms | 124597 | 640 | 4.49293e+08 | 118018 | 0.711163 | 2.45835 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 945.693 | 0.427189 | 6421.2ms | 124597 | 2560 | 7.37557e+08 | 125649 | 1.58687 | 2.61738 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 935.977 | 0.349514 | 6616.57ms | 124597 | 2560 | 5.04028e+08 | 126953 | 0.996636 | 2.64444 | 2(Tie) | true |
| Glaze | 866.316 | 0.94954 | 7110.69ms | 124597 | 320 | 5.428e+08 | 137161 | 0.438444 | 2.85717 | 4(Loss) | true |
