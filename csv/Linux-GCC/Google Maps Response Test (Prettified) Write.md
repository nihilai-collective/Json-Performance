
----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 32352.5 | 0.0660317 | 96.1742ms | 31235 | 320 | 118.283 | 920.734 | 0.110862 | 0.0744038 | 1(Win) | true |
| Glaze | 5645.73 | 0.079343 | 523.081ms | 31235 | 30 | 525.752 | 5276.2 | 0.151855 | 0.436339 | 2(Loss) | true |
| simdjson (reflection) | 585.217 | 0.205316 | 5315.38ms | 31235 | 320 | 3.49497e+06 | 50900.8 | 0.288222 | 4.22855 | 3(Loss) | true |
